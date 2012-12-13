class AddDefaultToUserRights < ActiveRecord::Migration
  def change
    change_table :users do |t|
      t.change :rights, :integer, :default => 0
    end
  end
end