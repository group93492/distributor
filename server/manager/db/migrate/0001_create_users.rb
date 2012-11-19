class CreateUsers < ActiveRecord::Migration
  def change
    create_table :users do |t|
      t.string :login, :null => false
      t.string :encrypted_password, :null => false
      t.integer :rights, :default => 0

      t.timestamps
    end
  end
end