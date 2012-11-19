class FoldersUsersAssociation < ActiveRecord::Migration
  def change
    create_table :folders_users do |t|
      t.references :users
      t.references :folders
    end
  end
end