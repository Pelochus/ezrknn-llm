#!/bin/bash

# Always useful
apt update && apt full-upgrade -y

# Update repo without updating image
cd /ezrknn-llm
git pull

bash
