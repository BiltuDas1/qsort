#!/bin/bash

git config --local user.email "41898282+github-actions[bot]@users.noreply.github.com"
git config --local user.name "github-actions[bot]"
git add .
git commit -m "Updated debian control information" && echo File Updated || echo Already up-to-date