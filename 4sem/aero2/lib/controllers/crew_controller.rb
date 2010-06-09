class CrewController < Controller
  def edit
    if @cgi.params.has_key?('is_commit')
      @item = Crew.find_by_flight_id(@db, @cgi.params['flight_id'][0])
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
        unless (s = @item.save(@db)) == 0
          @message = "---Экипаж назначен---"
	else
	  @message = "Ошибка БД"
	end
	render_template('edit')
      end      
    else
      if @cgi.params.has_key?('flight_id') 
        @item = Crew.find_by_flight_id(@db, @cgi.params['flight_id'][0])
	@message = "Редактирование экипажа"
        if @item.nil?
	@message = "Назначение нового экипажа"
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
end
