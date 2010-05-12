class FlightCheckInDeskController < Controller
  def show
    if @cgi.params.has_key?('check_in_desk_id') and @cgi.params['check_in_desk_id'][0] != ''
      @item = FlightCheckInDesk.find_by_id(@db, @cgi.params['check_in_desk_id'][0])
      render_template('show')
    else
      @message = 'Нет такой регистрационной стойки.'
      render_template('error')
    end
  end
end