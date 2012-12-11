require 'rubygems'
require 'bundler/setup'
require 'active_record'
require 'socket'
require 'ostruct'

# initializers
Dir[File.expand_path('../initializers/*.rb', __FILE__)].each {|file| require file}
# require all models
Dir[File.join("./app", "**/*.rb")].each {|file| require file}
# require all lib/core_ext
Dir[File.join("./lib/core_ext", "**/*.rb")].each {|file| require file}
