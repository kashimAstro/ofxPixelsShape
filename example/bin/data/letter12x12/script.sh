#!/bin/bash

for f in *.png; do
  convert -resize 12x $f $f
  echo $f
done

