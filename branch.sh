#!/usr/bin/bash

BRANCH_NAME=$1

git checkout -b "$BRANCH_NAME"
mkdir "$BRANCH_NAME"
cd "$BRANCH_NAME" || return
mkdir src
mkdir include
cd "$BRANCH_NAME" || return