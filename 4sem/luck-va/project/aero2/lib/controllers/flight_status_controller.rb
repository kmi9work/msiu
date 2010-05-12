class FlightStatusController < Controller
  def show
    @header = 'История статусов рейса'
    if @cgi.params.has_key?('flight_id') and @cgi.params['flight_id'][0] != ''  
      @items = FlightStatus.find_all_by_flight_id(@db, @cgi.params['flight_id'][0])
      @id = @cgi.params['flight_id'][0]
      render_template('show')
    else
      @message = "Error: No such flight"
      render_template('error')
    end
  end
  
  def edit
    if @user and !@user[:is_super]
      if @cgi.params.has_key?('flight_id') and @cgi.params['flight_id'][0] != ''
        @flight_id = @cgi.params['flight_id'][0]
        if @cgi.params.has_key?('is_commit')
          params = filter_for_params()
          @item = FlightStatus.new
          @header = 'Обновление статуса полёта'
          @message = 'Информация о рейса изменена'
          params.each do |k, v|
            @item[k] = v[0] if k != 'id' and v != ''
          end
          @item.save(@db)
        else
          @header = 'Обновление статуса полёта'
        end
        render_template('edit')
      else
        @message = "Неправильная ссылка"
        if @flight_id 
          @link = "controller=FlightStatus&action=show&flight_id=#{@flight_id}" 
        else
          if @cgi.params.has_key?('flight_id')
            @link = "controller=FlightStatus&action=show&flight_id=#{@cgi.params['flight_id'][0]}" 
          else
            @link = "controller=Flight&action=list"
          end
        end
        render_template('error')
      end
    else
      @message = 'У вас недостаточно прав'
      if @cgi.params.has_key?('flight_id')
        @link = "controller=FlightStatus&action=show&flight_id=#{@cgi.params['flight_id'][0]}" 
      else
        @link = "controller=Flight&action=list"
      end
      render_template('error')
    end
  end
  
  def destroy
    if params.has_key?('id') and params['id'][0] != ''
      @item = FlightStatus.find_all_by_id(@db, @cgi.params['id'][0])
      unless @item.nil?
        @item.destroy(@db)
        @message = 'Объект удален!'
      else
        @message = 'Объект не найден!'
      end
    end
    render_template(@action)
  end
end
