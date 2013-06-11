#!/bin/bash

sed '/<tag name=0/,/\/tag>/s/123/987/g' origin.txt > result.txt && diff origin.txt result.txt
