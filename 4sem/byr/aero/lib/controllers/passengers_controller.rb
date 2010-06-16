require 'db_core/models/passenger'
class PassengersController < Controller
  def is_authorized_action?()
    !([:easy_list].include?(@action))
  end
  def list()
    @items = Passenger.find_all(@db)
    render_template(@action)
  end

  def easy_list()
    @items = Passenger.find_all(@db)
    render_template(@action)
  end

 def edit()
    if @cgi.params.has_key?('is_commit')
      params = filter_for_params()
      if params.has_key?('id') and params['id'][0] != ''
        @item = Passenger.find_first(@db, params['id'][0])
        @header = 'Редактирование информации о пассажире'
        @message = 'Информация о пассажире записана'
        if @item.nil?
          @item = Passenger.new
          @header = 'Внесение новой информации о пассажире'
          @message = 'Информация о пассажире внесена в БД'
        end
      else
        @item = Passenger.new
        @header = 'Внесение новой информации о пассажире'
        @message = 'Информация о новом пассажире внесена в БД'
      end
        params.each do |k, v|
                @item[k] = v[0] if k != 'id' and v != ''
        end

 	@item.save(@db)
    else
      if @cgi.params.has_key?('id')
        @item = Passenger.find_first(@db, @cgi.params['id'][0])
        @header = 'Редактирование информации о пассажире'
        if @item.nil?
          @item = Passenger.new
          @header = 'Внесение новой информации о пассажире'
        end
      else
        @item = Passenger.new
        @header = 'Внесение новой информации о пассажире'
      end

    end

    render_template('edit')
  end

 def edit2()
    unless @cgi.params.has_key?('flight_id')
    	@message = "No flight_id"
	@link = "controller=Flights&action=list"
	render_template('error')
    else 
        @item = Passenger.new
        @header = 'Внесение новой информации о пассажире'
        if @cgi.params.has_key?('is_commit')
     	    params = filter_for_params()
	    params.each do |k, v|
                @item[k] = v[0] if k != 'id' and v != ''
            end
	    @item.save
        end

        render_template('edit2')
    end
  end

  def destroy()
    if @cgi.params.has_key?('id') and @cgi.params['id'][0] != ''
      @item = Passenger.find_first(@db, @cgi.params['id'][0])
      unless @item.nil?
        @item.destroy(@db)
        @message = 'Объект удален!'
      else
        @message = 'Объект не найден!'
      end
    end
    render_template(@action)
  end

  def PassengersController.actions(user) 
   result = [[:easy_list, 'Пассажиры']]    
    unless user.nil?
     result += [[:list, 'Все пассажиры']]
    end
    result
  end
end

