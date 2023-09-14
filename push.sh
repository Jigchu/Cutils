#!/usr/bin/bash

curr_dir=$PWD

cd "$(git rev-parse --show-toplevel)" || return
git push -u origin "$1"
git checkout main
git merge main "$1"
git push -u origin main
git checkout "$1"
cd "$curr_dir" || return 