class User < ActiveRecord::Base
  has_and_belongs_to_many :folders
  attr_accessible :login, :encrypted_password, :rights
  # attr_accessor :socket
  validates_uniqueness_of :login, :message => "must be unique"
  validates_presence_of :login, :message => "can't be blank"
  validates_presence_of :encrypted_password, :message => "can't be blank"

  def self.register_user(registration_request)
    User.create(:login => registration_request.username,
                :encrypted_password => registration_request.password)
  end
end
