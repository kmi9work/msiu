class SearchController < Controller
  def index 
    render_template('index')
  end
  def find
    if @cgi.params.has_key?('is_commit')
      params = filter_for_params
      @items = Passenger.search(@db, params)
      render_template('find')
    else
      @message = "Error, no is_commit!"
      render_template('index')
    end
  end
end
