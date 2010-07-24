#!/usr/bin/ruby
# -*- coding: utf-8 -*-
#
#Author:: Junsei Takahashi
#* last update 2010-07-24 11:54:28
#

require 'open-uri'

url = "http://twitter.com/powerbombkun"
open(url){|f| puts f.read }
