// Copyright (c) 2024 by Rockchip Electronics Co., Ltd. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Modified by Pelochus

#include <string.h>
#include <unistd.h>
#include <string>
#include "rkllm.h"
#include <fstream>
#include <iostream>
#include <csignal>
#include <vector>

using namespace std;

LLMHandle llmHandle = nullptr;

void exit_handler(int signal)
{
    if (llmHandle != nullptr)
    {
        {
            cout << "Program is about to exit..." << endl;
            LLMHandle _tmp = llmHandle;
            llmHandle = nullptr;
            rkllm_destroy(_tmp);
        }
    }

    exit(signal);
}

void callback(RKLLMResult *result, void *userdata, LLMCallState state)
{
    if (state == RKLLM_RUN_FINISH)
    {
        printf("\n");
    } else if (state == RKLLM_RUN_ERROR) {
        printf("\\run error\n");
    } else if (state == RKLLM_RUN_NORMAL) {
        /*
        ======================================================================================================================
        When using the GET_LAST_HIDDEN_LAYER function, the callback interface will return a memory pointer: last_hidden_layer,
        the number of tokens: num_tokens, and the hidden layer size: embd_size.
        These three parameters can be used to access the data in last_hidden_layer.

        Note: You must retrieve the data within the current callback; if not retrieved in time, the pointer will be released
        during the next callback.
        ======================================================================================================================
        */

        if (result->last_hidden_layer.embd_size != 0 && result->last_hidden_layer.num_tokens != 0) {
            int data_size = result->last_hidden_layer.embd_size * result->last_hidden_layer.num_tokens * sizeof(float);
            printf("\ndata_size:%d",data_size);
            ofstream outFile("last_hidden_layer.bin", ios::binary);

            if (outFile.is_open()) {
                outFile.write(reinterpret_cast<const char*>(result->last_hidden_layer.hidden_states), data_size);
                outFile.close();
                cout << "Data saved to output.bin successfully!" << endl;
            } else {
                cerr << "Failed to open the file for writing!" << endl;
            }
        }

        printf("%s", result->text);
    }
}

int main(int argc, char **argv)
{
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " model_path max_new_tokens max_context_len\n" << endl;
        return 1;
    }

    signal(SIGINT, exit_handler);
    printf("RKLLM starting, please wait...\n");

    // Set parameters and initialize
    RKLLMParam param = rkllm_createDefaultParam();
    param.model_path = argv[1];

    // Set sampling parameters
    param.top_k = 1;
    param.top_p = 0.95;
    param.temperature = 0.8;
    param.repeat_penalty = 1.1;
    param.frequency_penalty = 0.0;
    param.presence_penalty = 0.0;

    param.max_new_tokens = atoi(argv[2]);
    param.max_context_len = atoi(argv[3]);
    param.skip_special_token = true;
    param.extend_param.base_domain_id = 0;
    param.extend_param.embed_flash = 1;

    int ret = rkllm_init(&llmHandle, &param, callback);

    if (ret == 0){
        printf("rkllm init success\n");
    } else {
        printf("rkllm init failed\n");
        exit_handler(-1);
    }

    vector<string> pre_input;
    pre_input.push_back("Welcome to ezrkllm! This is an adaptation of Rockchip's rknn-llm repo (see github.com/airockchip/rknn-llm) for running LLMs on its SoCs' NPUs.\n");
    pre_input.push_back("\nTo exit the model, enter either exit or quit\n");
    pre_input.push_back("\nMore information here: https://github.com/Pelochus/ezrknpu");
    pre_input.push_back("\nDetailed information for devs here: https://github.com/Pelochus/ezrknn-llm");

    cout << "\n*************************** Pelochus' ezrkllm runtime *************************\n" << endl;

    for (int i = 0; i < (int) pre_input.size(); i++)
    {
        cout << "[" << i << "] " << pre_input[i] << endl;
    }

    cout << "\n*************************************************************************\n" << endl;

    RKLLMInput rkllm_input;

    // Initialize the infer parameter structure
    RKLLMInferParam rkllm_infer_params;
    memset(&rkllm_infer_params, 0, sizeof(RKLLMInferParam));  // Initialize all fields to 0

    // 1. Initialize and set LoRA parameters (if LoRA is to be used)
    // RKLLMLoraAdapter lora_adapter;
    // memset(&lora_adapter, 0, sizeof(RKLLMLoraAdapter));
    // lora_adapter.lora_adapter_path = "qwen0.5b_fp16_lora.rkllm";
    // lora_adapter.lora_adapter_name = "test";
    // lora_adapter.scale = 1.0;
    // ret = rkllm_load_lora(llmHandle, &lora_adapter);
    // if (ret != 0) {
    //     printf("\nload lora failed\n");
    // }

    // Load a second LoRA
    // lora_adapter.lora_adapter_path = "Qwen2-0.5B-Instruct-all-rank8-F16-LoRA.gguf";
    // lora_adapter.lora_adapter_name = "knowledge_old";
    // lora_adapter.scale = 1.0;
    // ret = rkllm_load_lora(llmHandle, &lora_adapter);
    // if (ret != 0) {
    //     printf("\nload lora failed\n");
    // }

    // RKLLMLoraParam lora_params;
    // lora_params.lora_adapter_name = "test";  // Specify the name of the LoRA to be used for inference
    // rkllm_infer_params.lora_params = &lora_params;

    // 2. Initialize and set Prompt Cache parameters (if prompt cache is to be used)
    // RKLLMPromptCacheParam prompt_cache_params;
    // prompt_cache_params.save_prompt_cache = true;                  // Whether to save the prompt cache
    // prompt_cache_params.prompt_cache_path = "./prompt_cache.bin";  // If saving, specify the cache file path
    // rkllm_infer_params.prompt_cache_params = &prompt_cache_params;

    // rkllm_load_prompt_cache(llmHandle, "./prompt_cache.bin"); // Load the cached prompt

    rkllm_infer_params.mode = RKLLM_INFER_GENERATE;
    // By default, the chat operates in single-turn mode (no context retention)
    // 0 means no history is retained, each query is independent
    rkllm_infer_params.keep_history = 0;

    // The model has a built-in chat template by default, which defines how prompts are formatted
    // for conversation. Users can modify this template using this function to customize the
    // system prompt, prefix, and postfix according to their needs.

    rkllm_set_chat_template(llmHandle, "", "<｜User｜>", "<｜Assistant｜>");

    while (true)
    {
        string input_str;
        printf("\n");
        printf("You: ");
        getline(cin, input_str);

        if (input_str == "exit" || input_str == "quit")
        {
            cout << "Quitting rkllm..." << endl;
            break;
        }

        if (input_str == "clear")
        {
            ret = rkllm_clear_kv_cache(llmHandle, 1);

            if (ret != 0)
            {
                printf("clear kv cache failed!\n");
            }

            continue;
        }

        for (int i = 0; i < (int)pre_input.size(); i++)
        {
            if (input_str == to_string(i))
            {
                input_str = pre_input[i];
                cout << input_str << endl;
            }
        }

        rkllm_input.input_type = RKLLM_INPUT_PROMPT;
        rkllm_input.prompt_input = (char *) input_str.c_str();
        printf("LLM: ");

        // To use standard inference functionality, set rkllm_infer_mode to RKLLM_INFER_GENERATE or leave it unset
        rkllm_run(llmHandle, &rkllm_input, &rkllm_infer_params, NULL);
    }

    rkllm_destroy(llmHandle);

    return 0;
}
