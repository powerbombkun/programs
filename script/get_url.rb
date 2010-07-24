#!/usr/bin/ruby
# -*- coding: utf-8 -*-
#
#Author:: Junsei Takahashi
#* last update 2010-07-24 11:57:06
#

require 'open-uri'

url = "http://www.google.co.jp/"
open(url){|f| puts f.read }
