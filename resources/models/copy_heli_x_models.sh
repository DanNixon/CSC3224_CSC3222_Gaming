#!/bin/bash

MODEL_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

HELI_X_MODEL_DIR="$1"/"$2"
MODEL_DIR="$MODEL_ROOT"/"$2"

echo $HELI_X_MODEL_DIR
echo $MODEL_DIR

mkdir -p $MODEL_DIR

for FT in obj mtl jpg png wav
do
  cp "$HELI_X_MODEL_DIR"/*.$FT $MODEL_DIR
done

cp -n $MODEL_ROOT/TEMPLATE.ini $MODEL_DIR/"$2".ini
