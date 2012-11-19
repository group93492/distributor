class CreateFolders < ActiveRecord::Migration
  def change
    create_table :folders do |t|
      t.string :path, :null => false

      t.timestamps
    end
  end
end