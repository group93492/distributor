class FixFoldersUsersAssociationReferencesNames < ActiveRecord::Migration
  def change
    change_table :folders_users do |t|
      t.rename :users_id, :user_id
      t.rename :folders_id, :folder_id
    end
  end
end