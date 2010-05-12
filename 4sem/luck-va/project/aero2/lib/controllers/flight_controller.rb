class FlightController < Controller
  def is_authorized_action?
    !([:departure_list, :arrival_list].include?(@action))
  end

  def list
    @items = Flight.find_all(@db)
    @header = 'Все рейсы'
    render_template('list')
  end

  def departure_list
    @items = Flight.find_all(@db, true)
    @header = 'Вылетающие рейсы'
    render_template('list')
  end

  def arrival_list
    @items = Flight.find_all(@db, false)
    @header = 'Прилетающие рейсы'
    render_template('list')
  end
  
  def show
    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = Flight.find_by_id(@db, @cgi.params['id'][0])
      puts @item.inspect
      unless @item
	@message = 'Нет такого рейса.'
	@link = 'controller=Flight&action=list'
	return render_template('error')
      end
      render_template('show')
    else
      @message = 'Ошибка.'
      render_template('error')
    end
  end

  def edit
    if @user and !@user[:is_super]
      if @cgi.params.has_key?('is_commit')
        params = filter_for_params()
        if params.has_key?('id') and params['id'][0] != ''
          if @item.nil?
            @item = Flight.new
            @header = 'Внесение новой информации о рейсах'
            @message = 'Информация о новом рейсе внесена в БД'
          else
            @item = Flight.find_by_id(@db, params['id'][0])
            @header = 'Редактирование информации о рейсе'
            @message = 'Информация о рейсе записана'
          end
        else
          @item = Flight.new
          @header = 'Внесение новой информации о рейсах'
          @message = 'Информация о новом рейсе внесена в БД'
        end
        params.each do |k, v|
          @item[k] = v[0] if k != 'id' and v != ''
        end
        @item.save(@db)
      else
        if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
          if @item.nil?
            @item = Flight.new
            @header = 'Внесение новой информации о рейсах'
          else
            @item = Flight.find_by_id(@db, @cgi.params['id'][0])
            @header = 'Редактирование информации о рейсе'
          end
        else
          @item = Flight.new
          @header = 'Внесение новой информации о рейсах'
        end
      end
      render_template('edit')
    else
      @message = 'У вас недостаточно прав'
      @link = 'controller=Flight&action=list'
      render_template('error')
    end
  end

  def destroy
    if @user and !@user[:is_super]
      if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
        @item = Flight.find_by_id(@db, @cgi.params['id'][0])
        unless @item.nil?
          @item.destroy(@db)
          @message = 'Объект удален!'
        else
          @message = 'Объект не найден!'
        end
      end
      render_template(@action)
    else
      @message = 'У вас недостаточно прав'
      @link = 'controller=Flight&action=list'
      render_template('error')
    end
  end

  def FlightController.actions(user)
    result = [[:departure_list, 'Вылетающие рейсы'],
              [:arrival_list, 'Прилетающие рейсы']]
    unless user.nil?
      result += [[:list, 'Все рейсы']]
    end
    result
  end
end
