# ezrknn-llm
This repo tries to make RKNN LLM usage easier for people who don't want to read through Rockchip's docs.

Main repo is https://github.com/Pelochus/ezrknpu where you can find more instructions, documentation... for general use.
This repo is intended for details in RKLLM and also how to convert models.

## Requirements
Keep in mind this repo is focused for:
- High-end Rockchip SoCs, mainly the RK3588
- Linux, not Android
- Linux kernels from Rockchip (as of writing 5.10 and 6.1 from Rockchip should work, if your board has one of these it will very likely be Rockchip's kernel)

## Quick Install
First clone the repo:

```bash
git clone https://github.com/Pelochus/ezrknn-llm
```

Then run:

```bash
cd ezrknn-llm && bash install.sh
```

## Test
Run (assuming you are on the folder where your `.rkllm` file is located):

```bash
rkllm qwen-chat-1_8B.rkllm # Or any other model you like
```

## Converting LLMs for Rockchip's NPUs
### Docker
In order to do this, you need a Linux PC x86 (Intel or AMD). Currently, Rockchip does not provide ARM support for converting models, so can't be done on a Orange Pi or similar.
Run:

`docker run -it pelochus/ezrkllm-toolkit:latest bash`

Then, inside the Docker container:

```bash
apt install -y python3-tk # This needs some configuring from your part 
cd ezrknn-llm/rkllm-toolkit/examples/huggingface/
```

Now change the `test.py` with your preferred model. This container provides Qwen-1.8B and LLaMa2 Uncensored. By default, Qwen-1.8B is selected. 
Before converting the model, remember to run `git lfs pull` to download the model.
To convert the model, run:

`python3 test.py`

## Fixing hallucinating LLMs
Check this reddit post if you LLM seems to be responding garbage:

https://www.reddit.com/r/RockchipNPU/comments/1cpngku/rknnllm_v101_lets_talk_about_converting_and/

# Original README starts below

<hr>
<hr>
<hr>

# Description
  RKLLM software stack can help users to quickly deploy AI models to Rockchip chips. The overall framework is as follows:
    <center class="half">
        <div style="background-color:#ffffff;">
        <img src="res/framework.jpg" title="RKLLM"/>
    </center>

  In order to use RKNPU, users need to first run the RKLLM-Toolkit tool on the computer, convert the trained model into an RKLLM format model, and then inference on the development board using the RKLLM C API.

- RKLLM-Toolkit is a software development kit for users to perform model conversionand quantization on PC.

- RKLLM Runtime provides C/C++ programming interfaces for Rockchip NPU platform to help users deploy RKLLM models and accelerate the implementation of LLM applications.

- RKNPU kernel driver is responsible for interacting with NPU hardware. It has been open source and can be found in the Rockchip kernel code.

# Support Platform
  - RK3588 Series
  - RK3576 Series

# Support Models
  - [X] [TinyLLAMA 1.1B](https://huggingface.co/TinyLlama/TinyLlama-1.1B-Chat-v1.0/tree/fe8a4ea1ffedaf415f4da2f062534de366a451e6) 
  - [X] [Qwen 1.8B](https://huggingface.co/Qwen/Qwen-1_8B-Chat/tree/1d0f68de57b88cfde81f3c3e537f24464d889081)
  - [X] [Qwen2 0.5B](https://huggingface.co/Qwen/Qwen1.5-0.5B/tree/8f445e3628f3500ee69f24e1303c9f10f5342a39)
  - [X] [Phi-2 2.7B](https://hf-mirror.com/microsoft/phi-2/tree/834565c23f9b28b96ccbeabe614dd906b6db551a)
  - [X] [Phi-3 3.8B](https://huggingface.co/microsoft/Phi-3-mini-4k-instruct/tree/291e9e30e38030c23497afa30f3af1f104837aa6)
  - [X] [ChatGLM3 6B](https://huggingface.co/THUDM/chatglm3-6b/tree/103caa40027ebfd8450289ca2f278eac4ff26405)
  - [X] [Gemma 2B](https://huggingface.co/google/gemma-2b-it/tree/de144fb2268dee1066f515465df532c05e699d48)
  - [X] [InternLM2 1.8B](https://huggingface.co/internlm/internlm2-chat-1_8b/tree/ecccbb5c87079ad84e5788baa55dd6e21a9c614d)
  - [X] [MiniCPM 2B](https://huggingface.co/openbmb/MiniCPM-2B-sft-bf16/tree/79fbb1db171e6d8bf77cdb0a94076a43003abd9e)

# Download
- You can also download all packages, docker image, examples, docs and platform-tools from [RKLLM_SDK](https://console.zbox.filez.com/l/RJJDmB), fetch code: rkllm

# RKNN Toolkit2
If you want to deploy additional AI model, we have introduced a SDK called RKNN-Toolkit2. For details, please refer to:

https://github.com/airockchip/rknn-toolkit2

# CHANGELOG
## v1.0.1
 - Optimize model conversion memory occupation
 - Optimize inference memory occupation
 - Increase prefill speed
 - Reduce initialization time
 - Improve quantization accuracy
 - Add support for Gemma, ChatGLM3, MiniCPM, InternLM2, and Phi-3
 - Add Server invocation
 - Add inference interruption interface
 - Add logprob and token_id to the return value

for older version, please refer [CHANGELOG](CHANGELOG.md)
