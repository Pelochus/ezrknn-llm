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

#define PROMPT_TEXT_PREFIX "<|im_start|>system You are a helpful assistant. <|im_end|> <|im_start|>user"
#define PROMPT_TEXT_POSTFIX "<|im_end|><|im_start|>assistant"

using namespace std;

LLMHandle llmHandle = nullptr;

void exit_handler(int signal)
{
    if (llmHandle != nullptr)
    {
        cout << "Catched exit signal. Exiting..." << endl;
        LLMHandle _tmp = llmHandle;
        llmHandle = nullptr;
        rkllm_destroy(_tmp);
        exit(signal);
    }
}

void callback(const char *text, void *userdata, LLMCallState state)
{
    if (state == LLM_RUN_FINISH)
    {
        printf("\n");
    }
    else if (state == LLM_RUN_ERROR)
    {
        printf("\\LLM run error\n");
    }
    else
    {
        printf("%s", text);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s [rkllm_model_path]\n", argv[0]);
        return -1;
    }
    
    signal(SIGINT, exit_handler);
    string rkllm_model(argv[1]);
    printf("RKLLM starting, please wait...\n");

    RKLLMParam param = rkllm_createDefaultParam();
    param.modelPath = rkllm_model.c_str();
    param.target_platform = "rk3588";
    param.num_npu_core = 2;
    param.top_k = 1;
    param.max_new_tokens = 256;
    param.max_context_len = 512;
    
    rkllm_init(&llmHandle, param, callback);
    printf("RKLLM init success!\n");
    
    vector<string> pre_input;
    pre_input.push_back("Welcome to ezrkllm! This is an adaptation of Rockchip's rknn-llm repo (see github.com/airockchip/rknn-llm) for running LLMs on its SoCs' NPUs.\n");
    pre_input.push_back("You are currently running the runtime for ");
    pre_input.push_back(param.target_platform);
    pre_input.push_back("\nTo exit the model, enter either exit or quit\n");
    pre_input.push_back("\nMore information here: https://github.com/Pelochus/ezrknpu");
    pre_input.push_back("\nDetailed information for devs here: https://github.com/Pelochus/ezrknn-llm");
    
    cout << "\n*************************** Pelochus' ezrkllm runtime *************************\n" << endl;
    
    for (int i = 0; i < (int)pre_input.size(); i++)
    {
        cout << pre_input[i];
    }
    
    cout << "\n*******************************************************************************\n" << endl;

    string text;
    while (true)
    {
        std::string input_str;
        printf("\n");
        printf("You: ");
        std::getline(std::cin, input_str);
        
        if (input_str == "exit" || input_str == "quit")
        {
            cout << "Quitting program..." << endl;
            break;
        }
        
        for (int i = 0; i < (int)pre_input.size(); i++)
        {
            if (input_str == to_string(i))
            {
                input_str = pre_input[i];
                cout << input_str << endl;
            }
        }
        
        string text = PROMPT_TEXT_PREFIX + input_str + PROMPT_TEXT_POSTFIX;
        printf("LLM: ");
        rkllm_run(llmHandle, text.c_str(), NULL);
    }

    rkllm_destroy(llmHandle);

    return 0;
}
