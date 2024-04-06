#!/bin/bash

# Dependencies
apt update
apt install -y python3 pip git curl wget nano sudo # python3-tk

# Better than using the default from Rockchip
curl https://raw.githubusercontent.com/Pelochus/ezrknn-llm/master/install.sh | sudo bash

# For running the test.py
pip install /ezrknn-llm/rkllm-toolkit/packages/rkllm_toolkit-1.0.0-cp38-cp38-linux_x86_64.whl

# Clone some compatible LLMs
cd /ezrknn-llm/rkllm-toolkit/examples/huggingface
git clone https://huggingface.co/Qwen/Qwen-1_8B-Chat
git clone https://huggingface.co/georgesung/llama2_7b_chat_uncensored