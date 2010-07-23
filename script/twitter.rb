#!/usr/bin/ruby
# -*- coding: utf-8 -*-
#
#Author:: Junsei Takahashi
#* last update 2010-07-24 00:48:26
#
require 'rubygems'
require 'twitter'

USERNAME = ''
PASSWORD = ''

client = Twitter::Base.new( Twitter::HTTPAuth.new( USERNAME, PASSWORD ) )
client.update("hoge")

