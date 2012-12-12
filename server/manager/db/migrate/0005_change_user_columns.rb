class ChangeUserColumns < ActiveRecord::Migration
  def change
    change_table :users do |t|
      t.change :login, :string, :null => true
      t.change :encrypted_password, :string, :null => true
      t.change :rights, :integer, :default => nil
    end
  end
end