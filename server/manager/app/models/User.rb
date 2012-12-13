class User < ActiveRecord::Base
  has_and_belongs_to_many :folders
  attr_accessible :login, :encrypted_password, :rights
  attr_accessor :online, :socket
  validates_uniqueness_of :login, :message => "must be unique"
  validates_presence_of :login, :message => "can't be blank"
  validates_presence_of :encrypted_password, :message => "can't be blank"

  def self.register_user(registration_request)
    User.create(:login => registration_request.username,
                :encrypted_password => registration_request.password)
  end

  def self.authorize_user(authorization_request, socket)
    user = User.find_by_login_and_encrypted_password(authorization_request.username,
                                                     authorization_request.password)
    if user
      user.authanticate!(socket)
    else
      nil
    end
  end

  def authanticate!(socket)
    self.online = true
    self.socket = socket
  end
end
