class CheckInDeskController < Controller
  def list
    @items = CheckInDesk.find_all(@db)
    @header = 'Регистрационные стойки'
    render_template('list')
  end
  def edit
    if @user and !@user[:is_super]
      if @cgi.params.has_key?('is_commit')
        params = filter_for_params()
        if params.has_key?('id') and params['id'][0] != ''
          if @item.nil?
            @item = CheckInDesk.new
            @header = 'Добавление посадочного регистрационной стойки'
            @message = 'Регистрационная стойка записана'
          else
            @item = CheckInDesk.find_by_id(@db, params['id'][0])
            @header = 'Редактирование регистрационной стойки'
            @message = 'Информация о регистрационной стойке'
          end
        else
          @item = CheckInDesk.new
          @header = 'Добавление регистрационной стойки'
          @message = 'Регистрационная стойка записана'
        end
        params.each do |k, v|
          @item[k] = v[0] if k != 'id' and v != ''
        end
        @item.save(@db)
      else
        if @cgi.params.has_key?('id')
          @item = CheckInDesk.find_by_id(@db, @cgi.params['id'][0])
          if @item.nil?
            @item = CheckInDesk.new
            @header = 'Добавление регистрационной стойки'
          else
            @header = 'Редактирование регистрационной стойки'
          end
        else
          @item = CheckInDesk.new
          @header = 'Внесение новой информации о регистрационной стойке'
        end
      end
      render_template('edit')
    else
      @message = 'Недостаточно прав'
      @link = 'controller=CheckInDesk&action=list'
      render_template('error')
    end
  end
  def destroy()
    if @user and !@user[:is_super]
      if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
        @item = CheckInDesk.find_by_id(@db, @cgi.params['id'][0])
        unless @item.nil?
          @item.destroy(@db)
          @message = 'Объект удален!'
        else
          @message = 'Объект не найден!'
        end
      end
      render_template(@action)
    else
      @message = 'Недостаточно прав'
      @link = 'controller=CheckInDesk&action=list'
      render_template('error')
    end
  end
  
end