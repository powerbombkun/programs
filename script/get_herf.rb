#!/usr/bin/ruby
# -*- coding: utf-8 -*-
#
#Author:: Junsei Takahashi
#* last update 2010-07-24 12:04:43
#
require 'rubygems'
require 'hpricot'
require 'kconv'
require 'open-uri'
doc = Hpricot(open("http://hatena.ne.jp/"))

hrefs = (doc/:a).map {|elem| elem[:href]}

hrefs.each{ |i| puts i}
