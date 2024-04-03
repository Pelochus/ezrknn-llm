#!/bin/bash

# Made by Pelochus
# Check for more info: https://github.com/Pelochus/ezrknn-llm/

message_print() {
  echo
  echo "#########################################"
  echo $1
  echo "#########################################"
  echo
}

message_print "Checking root permission..."

if [ "$EUID" -ne 0 ]; then 
  echo "Please run this script as root!"
  exit
fi

# message_print "Changing to repository..."

# git clone https://github.com/Pelochus/ezrknn-llm.git
# cd ezrknn-llm/

message_print "Installing RKNN LLM libraries..."

cp ./rkllm-runtime/runtime/Linux/librkllm_api/aarch64/* /usr/lib
cp ./rkllm-runtime/runtime/Linux/librkllm_api/include/* /usr/local/include

message_print "Compiling LLM runtime for Linux..."

cd ./rkllm-runtime/example
bash build-linux.sh

message_print "Moving rkllm to /usr/bin..."

cp ./build/build_linux_aarch64_Release/llm_demo /usr/bin/rkllm # We also change the name for remembering how to call it from shell

message_print "Increasing file limit for all users (needed for LLMs to run)..."

echo "* soft nofile 16384" >> /etc/security/limits.conf
echo "* hard nofile 1048576" >> /etc/security/limits.conf

message_print "Done installing ezrknn-llm!"
