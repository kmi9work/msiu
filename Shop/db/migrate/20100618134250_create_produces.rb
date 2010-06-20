class CreateProduces < ActiveRecord::Migration
  def self.up
    create_table :produces do |t|
      t.column :name, :text, :null => false
      t.column :size_x, :float
      t.column :size_y, :float
      t.column :size_z, :float
      t.column :weight, :float
      t.column :prms, :text
      t.column :reason, :text, :null => false
      t.column :catalogue, :integer
      t.column :price, :text
      t.column :storage, :text
      t.timestamps
    end

    
  end

  def self.down
    drop_table :produces
  end
end
