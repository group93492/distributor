require 'active_record'
require 'yaml'

dbconfig = YAML::load(File.open(File.expand_path('../../database.yml', __FILE__)))
ActiveRecord::Base.establish_connection(dbconfig)