class FlightTerminalController < Controller
  def list
    @items = FlightTerminal.find_all(@db)
    render_template('list')
  end

  def show
    if @cgi.params.has_key?('terminal_id') and @cgi.params['terminal_id'][0] != ''
      @item = FlightTerminal.find_by_id(@db, @cgi.params['terminal_id'][0])
      render_template('show')
    else
      @message = 'Нет такого терминала.'
      render_template('error')
    end
  end
end