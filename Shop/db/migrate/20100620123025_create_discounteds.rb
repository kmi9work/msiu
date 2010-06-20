class CreateDiscounteds < ActiveRecord::Migration
  def self.up
    create_table :discounteds do |t|
      t.column :name, :text, :null => false
      t.column :size_x, :float
      t.column :size_y, :float
      t.column :size_z, :float
      t.column :weight, :float
      t.column :prms, :text
      t.column :reason, :text
      t.column :sort, :text
      t.column :catalogue, :integer
      t.column :price, :text
      t.column :storage, :text
      t.timestamps
    end
  end

  def self.down
    drop_table :discounteds
  end
end
