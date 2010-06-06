class FlyPersonalController < Controller
  def is_authorized_action?()
    !([:easy_list].include?(@action))
  end
  
  def list()
    @items = FlyPersonal.find_all(@db)
    render_template(@action)
  end
  
  def fly_personals_list()
    @items = FlyPersonal.find_all(@db)
    @header = 'Персонал'
    render_template('list')
  end
  
  def edit()
    if @cgi.params.has_key?('is_commit')
      params = filter_for_params()
      if params.has_key?('id') and params['id'][0] != ''
        @item = FlyPersonal.find_first(@db, params['id'][0])
        @header = 'Редактирование'
        @message = 'Записано'
        if @item.nil?
          @item = FlyPersonal.new
          @header = 'Создание'
          @message = 'Создано'
        end
      else
        @item = FlyPersonal.new
        @header = 'Создание'
        @message = 'Создано'
      end
      params.each do |k, v|
        @item[k] = v[0] if k != 'id' and v != ''
      end
      @item.save(@db)
    else
      if @cgi.params.has_key?('id')
        @item = FlyPersonal.find_first(@db, @cgi.params['id'][0])
        @header = 'Редактирование'
        if @item.nil?
          @item = FlyPersonal.new
          @header = 'Создание'
        end
      else
        @item = FlyPersonal.new
        @header = 'Создание'
      end
    end
    render_template('edit')
  end
  
  def destroy()
    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = FlyPersonal.find_first(@db, @cgi.params['id'][0])
      unless @item.nil?
        @item.destroy(@db)
        @message = 'Объект удалён'
      else
        @message = 'Объект не найден'
      end
    end
    render_template(@action)
  end
  def FlyPersonal.actions(user)
    unless user.nil?
      result = [[:list, 'Все рейсы'], [:list, 'lol']]
    end
    result
  end

end
