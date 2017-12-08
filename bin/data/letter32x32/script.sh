#!/bin/bash

for f in *.png; do
  convert -negate $f $f
done

