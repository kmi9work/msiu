class ItemsController < ApplicationController
  layout 'operator_layout'

  def list
    unless params['catalogue_id'].blank?
      @items = Item.find(:all, :conditions => ['catalogue_id = ?', params['catalogue_id']])
    else
      @items = Item.find(:all)
    end
  end

  def create
  end

  def add_attribute()
    last_item = params[:last_item]
    return if last_item.blank?
    next_item = (last_item.to_i + 1).to_s

    render(:update) do |page|
      page.add_row(last_item, next_item)
    end
  end

  def create_commit
    rollback = false
    id = nil
    Item.transaction do
      ItemPeriod.transaction do
        ItemStorage.transaction do
          i = Item.new
          edit_item(i)
          id = i.catalogue_id
          rollback = true if @needs_to_validate.size > 0
          raise ActiveRecord::Rollback if rollback
        end
        raise ActiveRecord::Rollback if rollback
      end
      raise ActiveRecord::Rollback if rollback
    end
    unless rollback
      redirect_to(:action => :list, :catalogue_id => id, :user_name => @user)
    else
      redirect_to(:action => :list, :user_name => @user)
    end
  end

  def edit
    @item = Item.find(params[:id])
    redirect_to(:action => :list, :user_name => @user) if @item.nil?
  end

  def edit_commit
    id = nil
    rollback = false
    ItemPeriod.transaction do
      ItemStorage.transaction do
        Item.transaction do
          i = Item.find(params[:item][:id])
          unless i.nil?
            edit_item(i)
            id = i.catalogue_id
          end
          rollback = true if @needs_to_validate.size > 0
          raise ActiveRecord::Rollback if rollback
        end
        raise ActiveRecord::Rollback if rollback
      end
      raise ActiveRecord::Rollback if rollback
    end
    unless id.nil?
      redirect_to(:action => :list, :catalogue_id => id, :user_name => @user)
    else
      redirect_to(:action => :list, :user_name => @user)
    end
  end

  def edit_item(i)
    i.attributes = params[:item]
    prms = Hash.new
    if params.has_key?('prms') and params['prms'].has_key?('key') and
        params['prms'].has_key?('value')
      params['prms']['key'].each_key do |n|
        key = params['prms']['key'][n]
        value = params['prms']['value'][n]
        prms[key] = value unless key.blank?
      end
    end
    i.prms = prms
    i.save
    needs_to_validate(i)
    if params.has_key?('deleted_period')
      params['deleted_period'].each do |k, v|
        unless k.blank? or v.blank?
          period = ItemPeriod.find(v)
          period.destroy
        end
      end
    end
    if params.has_key?('item_period')
      if params['item_period'].has_key?('start_date') and
          params['item_period'].has_key?('end_date') and
          params['item_period'].has_key?('price')
        params['item_period']['start_date'].keys.each do |k|
          price = params['item_period']['price'][k]
          unless price.blank?
            period = ItemPeriod.new
            period.start_date = params['item_period']['start_date'][k]
            period.end_date = params['item_period']['end_date'][k]
            period.price = price
            period.item = i
            period.save
            needs_to_validate(period)
          end
        end
      end
    end
    if params.has_key?('deleted_storage')
      params['deleted_storage'].each do |k, v|
        unless k.blank? or v.blank?
          storage = ItemStorage.find(v)
          storage.destroy
        end
      end
    end
    if params.has_key?('item_storage')
      if params['item_storage'].has_key?('quantity') and
          params['item_storage'].has_key?('storage_id')
        params['item_storage']['quantity'].keys.each do |k|
          quantity = params['item_storage']['quantity'][k]
          storage_id = params['item_storage']['storage_id'][k]
          unless quantity.blank? or storage_id.blank?
            storage = ItemStorage.find(:first,
              :conditions => ['storage_id = ? AND item_id = ?',
                storage_id, i.id])
            if storage.nil?
              storage = ItemStorage.new
              storage.quantity = quantity
              storage.storage_id = params['item_storage']['storage_id'][k]
              storage.item = i
            else
              storage.quantity += quantity.to_i
            end
            storage.save
            needs_to_validate(storage)
          end
        end
      end
    end
  end

  def destroy
    i = Item.find(params[:id])
    unless i.nil?
      id = i.catalogue_id
      i.destroy
      redirect_to(:action => :list, :catalogue_id => id, :user_name => @user)
    else
      redirect_to(:action => :list, :user_name => @user)
    end
  end

  def show
    @item = Item.find(params[:id])
  end

  def ItemsController.menu_items(user_class)
    return [[:list, 'Товары']] unless user_class == 'operator'
    return [[:list, 'Товары'], [:create, 'Новый товар']]
  end

  def ItemsController.inline_menu_items(user_class)
    return [[:show, 'Показать']] unless user_class == 'operator'
    return [[:show, 'Показать'], [:edit, 'Редактировать'], 
            [:destroy, 'Удалить'], [:list, 'Поставки', :providings]]
  end
end
