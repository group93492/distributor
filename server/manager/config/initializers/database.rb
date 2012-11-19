require 'yaml'
require 'logger'

dbconfig = YAML::load(File.open(File.expand_path('../../database.yml', __FILE__)))
ActiveRecord::Base.establish_connection(dbconfig)
ActiveRecord::Base.logger = Logger.new(File.open('log/database.log', 'a'))
ActiveSupport::LogSubscriber.colorize_logging = false
