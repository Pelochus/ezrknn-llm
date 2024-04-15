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
cd ezrknn-llm/rkllm-toolkit/examples/huggingface/
```

Now change the `test.py` with your preferred model. This container provides Qwen-1.8B since it is the best working one and very lightweight. 
Before converting the model, remember to run `git lfs pull` to download the model.
To convert the model, run:

`python3 test.py`

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

# Download
- You can also download all packages, docker image, examples, docs and platform-tools from [RKLLM_SDK](https://console.zbox.filez.com/l/RJJDmB), fetch code: rkllm

# RKNN Toolkit2
If you want to deploy additional AI model, we have introduced a new SDK called RKNN-Toolkit2. For details, please refer to:

https://github.com/airockchip/rknn-toolkit2

# Notes

Due to recent updates to the Phi2 model, the current version of the RKLLM SDK does not yet support these changes. 
Please ensure to download a version of the [Phi2](https://hf-mirror.com/microsoft/phi-2/tree/834565c23f9b28b96ccbeabe614dd906b6db551a) model that is supported. 

# CHANGELOG

## v1.0.0-beta
 - Supports the conversion and deployment of LLM models on RK3588/RK3576 platforms
 - Compatible with Hugging Face model architectures
 - Currently supports the models LLaMA, Qwen, Qwen2, and Phi-2
 - Supports quantization with w8a8 and w4a16 precision
