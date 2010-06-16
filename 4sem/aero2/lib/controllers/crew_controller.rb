class CrewController < Controller
  def edit
    if @cgi.params.has_key?('is_commit')
      @item = nil
      if @cgi.params.has_key?('id')  
        @item = Crew.find_first(@db, @cgi.params['id'][0])
      end
      if @item.nil?
        @item = Crew.new
      end
      params = filter_for_params
      if params['stuard1_id'][0] == params['stuard2_id'][0]
        @message = "Стюарды должны быть разными"
        render_template('edit')
      else
        params.each do |k, v|
          @item[k] = v[0] if k != 'id' and v != ''
        end
        @item.save(@db)
        @message = "Экипаж назначен"
        render_template('edit')
      end
    else
      if @cgi.params.has_key?('id') 
        @item = Crew.find_first(@db, @cgi.params['id'][0])
        @message = "Редактирование экипажа"
        if @item.nil?
          @message = "Создание нового экипажа"
          @item = Crew.new
        end
        render_template('edit')
      else
        @message = "error: No flight_id"
        @link = "controller=FlyPersonal&action=list"
        render_template('error')
      end
    end
  end 
  def show
    if @cgi.params.has_key?('flight_id') 
      @item = Crew.find_by_flight_id(@db, @cgi.params['flight_id'][0])
      if @item.nil?
        @message = "у рейса ещё нет экипажа"
        render_template('error')
      else
        render_template('show')
      end
    else
      @message = "error: No flight_id"
      @link = "controller=FlyPersonal&action=list"
      render_template('error')
    end
  end
  def list
    @items = Crew.find_all(@db)
    render_template('list')
  end
  def choose_flight
    @id = @cgi.params[:id][0].to_i
    @item = Crew.find_first(@db, @id)
    if @item[:flight_id]
      @selected = @item[:flight_id] 
      @message = 'Редактирование рейса для экипажа'
    else
      @message = 'Назначение рейса для экипажа'
    end
    render_template('choose_flight')
  end
  def set_flight
    if @cgi.params.has_key?('is_commit')
      if @cgi.params.has_key?('id')
        @item = Crew.find_first(@db, @cgi.params['id'][0])
        params = filter_for_params
        
        if @item[:flight_id]
          new_flight = Flight.find_first(@db, params['flight_id'][0])
          if Time.parse(new_flight[:departure_date]) - Time.parse(@item.flight[:arrival_date]) < 12*3600
            @message = 'Между предыдущим рейсом и новым менее 12 часов'
            render_template('choose_flight')
          elsif new_flights[:departure_place] != @item.flight[:arrival_place]
            @message = "Место вылета отличается от места предыдущей посадки.\nМесто посадки: #{@item.flight[:arrival_place]}\nМесто вылета: #{new_flights[:departure_place]}"
            render_template('choose_flight')
          else
            @item[:flight_id] = params['flight_id'][0]
            @item.save(@db)
            @message = 'Рейс назначен'
            render_template('choose_flight')
          end
        end
      else
        @message = "error: No id"
        @link = "controller=Crew&action=list"
        render_template('error')
      end
    else
      @message = "error: No is_commit"
      @link = "controller=Crew&action=list"
      render_template('error')
    end
  end
end
