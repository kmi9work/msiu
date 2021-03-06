module Helper
  def companies_select(name, selected)
    "<select name = '#{name}'>" +
      Company.find_all(@db).map do |c|
        if c[:id].to_i == selected.to_i
          "<option value = '#{c[:id]}' selected>#{c[:name]}</option>"
        else
          "<option value = '#{c[:id]}'>#{c[:name]}</option>"
        end
      end.join("\n") +
      "</select>"
  end

  def is_departure_select(name, selected = true)
    options = {:true => 'отлетающий', :false => 'прилетающий'}
    "<select name = '#{name}'>" +
      options.map do |k, v|
        "<option value = '#{k}'#{k.to_s == selected.to_s ? ' selected' : ''}>#{v}</option>"
      end.join("\n") + 
      "</select>"
  end
  
  def status_select(name, selected)
    sum = ""
    FlightStatus::STATUSES.each do |status, i|
      sum += "<option value = '#{status}' #{status.to_s == selected.to_s ? ' selected' : ''}>#{i}</option>"
    end
    "<select name='#{name}'" +  
      sum + 
    "</select>"
  end
  
  def superuser_select(name, selected)
    "
    <select name='#{name}'> 
      <option value = '1'#{selected ? ' selected' : ''}>Да</option>
      <option value = '0'#{selected ? '' : ' selected'}>Нет</option>
    </select>
    "
  end
end
