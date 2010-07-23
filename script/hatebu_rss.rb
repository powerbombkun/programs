#!/usr/bin/ruby
# -*- coding: utf-8 -*-
#
#Author:: Junsei Takahashi
#* last update 2010-07-24 00:37:33
#
require 'open-uri'
require 'rss/1.0'
require 'rss/dublincore'

# Open XML(RSS) and Make RSS Object
bookmark = "http://b.hatena.ne.jp/hotentry.rss"
rss = open(bookmark){ |file| RSS::Parser.parse(file.read, false) }

# Set Output Encoding
rss.output_encoding = "UTF-8"

puts rss.channel.title
puts rss.channel.link
puts rss.channel.description
puts "------"
# Set HatebItem instance field
rss.items.each{ |item|
        puts item.title
        puts item.link
        puts item.description
        puts item.dc_date
        puts item.dc_creator
        item.dc_subjects.each{ |tag|
          print tag.content, ", "
        }
        puts ""
        puts "------"
}


