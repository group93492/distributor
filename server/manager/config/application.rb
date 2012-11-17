# initializers
Dir[File.expand_path('../initializers/*.rb', __FILE__)].each {|file| require file}