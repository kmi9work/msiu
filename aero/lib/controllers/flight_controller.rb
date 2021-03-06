class FlightController < Controller
  def is_authorized_action?()
    !([:departure_list, :arrival_list].include?(@action))
  end

  def list()
    @items = Flight.find_all(@db)
    render_template(@action)
  end

  def departure_list()
    @items = Flight.find_all(@db, true)
    @header = 'Вылетающие рейсы'
    render_template('easy_list')
  end

  def arrival_list()
    @items = Flight.find_all(@db, false)
    @header = 'Прилетающие рейсы'
    render_template('easy_list')
  end

  def edit()
    if @cgi.params.has_key?('is_commit')
      params = filter_for_params()
      if params.has_key?('id') and params['id'][0] != ''
        @item = Flight.find_first(@db, params['id'][0])
        @header = 'Редактирование информации о рейсе'
        @message = 'Информация о рейсе записана'
        if @item.nil?
          @item = Flight.new
          @header = 'Внесение новой информации о рейсах'
          @message = 'Информация о новом рейсе внесена в БД'
        end
      else
        @item = Flight.new
        @header = 'Внесение новой информации о рейсах'
        @message = 'Информация о новом рейсе внесена в БД'
      end
      if @item.crew
        if @item.crew.flights.size > 0
          if Date.parse(params['departure_date'][0]) - @item.crew.flights[-1][:arrival_date] < 12
            @message = 'Между предыдущим рейсом и новым менее 12 часов'
            return render_template('edit')
          elsif params['departure_place'][0] != @item.crew.flights[-1][:arrival_place]
            @message = "Место вылета отличается от места предыдущей посадки.<br>Место посадки: 
            #{@item.flights[-1][:arrival_place]}<br>Место вылета: #{new_flight[:departure_place]}"
            return render_template('edit')
          end
        end
      end
      params.each do |k, v|
        @item[k] = v[0] if k != 'id' and v != ''
      end
      @item.save(@db)
    else
      if @cgi.params.has_key?('id')
        @item = Flight.find_first(@db, @cgi.params['id'][0])
        @header = 'Редактирование информации о рейсе'
        if @item.nil?
          @item = Flight.new
          @header = 'Внесение новой информации о рейсах'
        end
      else
        @item = Flight.new
        @header = 'Внесение новой информации о рейсах'
      end
    end
    render_template('edit')
  end

  def destroy()
    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = Flight.find_first(@db, @cgi.params['id'][0])
      unless @item.nil?
        @item.destroy(@db)
        @message = 'Объект удален!'
      else
        @message = 'Объект не найден!'
      end
    end
    render_template(@action)
  end
  
  def show
    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = Flight.find_first(@db, @cgi.params['id'][0])
      render_template('show')
    else
      @message = "Ошибка! Нет id."
      @link = "controller=Flight&action=list"
      render_template('error')
    end
  end

  def FlightController.actions(user)
    result = [[:departure_list, 'Вылетающие рейсы'],
              [:arrival_list, 'Прилетающие рейсы']]
    unless user.nil?
      result = [[:list, 'Все рейсы']]
    end
    result
  end
end
