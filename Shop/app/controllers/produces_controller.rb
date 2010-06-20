class ProducesController < ApplicationController
  layout 'operator_layout'


=begin
  def edit
    @item = Produce.find(params[:id])
    redirect_to(:action => :list, :user_name => @user) if @item.nil?
  end

  def edit_commit
    c = Produce.find(params['Produce']['id'])
    unless c.nil?
      c.attributes = params['Produce']
      c.save
      needs_to_validate(c)
    end
    redirect_to(:action => :list, :user_name => @user)
  end
=end
  def destroy
    c = Produce.find(params[:id])
    c.destroy unless c.nil?
    redirect_to(:action => :list, :user_name => @user)
  end


  def show
    @item = Produce.find(params[:id])
  end

  def list
    @items = Produce.find(:all)
  end

  def ProducesController.menu_items(user_class)
    return [] unless user_class == 'operator'
    return [[:list, 'Списанные товары']]
  end

  def ProducesController.inline_menu_items(user_class)
    return [] unless user_class == 'operator'
    return [[:show, 'Показать'],[:destroy, 'Удалить']]
  end
end
