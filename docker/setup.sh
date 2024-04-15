#!/bin/bash

# Dependencies
apt update
apt install -y python3 pip git curl wget nano sudo apt-utils

# Better than using the default from Rockchip
git clone https://github.com/Pelochus/ezrknn-llm/
cd ezrknn-llm
# Optional:
# git checkout dev-in-progress
bash install.sh

# For converting
export BUILD_CUDA_EXT=0
pip install /ezrknn-llm/rkllm-toolkit/packages/rkllm_toolkit-1.2.1b1-cp312-cp312-linux_x86_64.whl --break-system-packages

# Clone LLM
cd /ezrknn-llm/examples/DeepSeek-R1-Distill-Qwen-1.5B_Demo/export
git clone https://huggingface.co/deepseek-ai/DeepSeek-R1-Distill-Qwen-1.5B

# Done here to avoid cloning full repository for the Docker image
apt install -y git-lfs

# Needed
DEBIAN_FRONTEND=noninteractive apt install -y python3-tk

# cd DeepSeek-R1-Distill-Qwen-1.5B
# git lfs pull
