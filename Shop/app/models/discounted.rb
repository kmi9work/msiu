class Discounted < ActiveRecord::Base
  serialize :prms, Hash
  
  def catalogue_name()
    self.catalogue
  end
  
  def Discounted.ccreate(item, reason, sort)
    c = Discounted.new
    item.attributes.each do |key, value|
      c[key] = value unless key == 'catalogues_id'
    end
    c[:price] = item.price
    c[:catalogue] = item.catalogue_name
    c[:reason] = reason
    c[:sort] = sort
    c.save
  end
  
  def before_validation()
    self.attribute_names.each do |n|
      self[n] = self[n].strip if self[n].kind_of?(String)
    end
  end
end
