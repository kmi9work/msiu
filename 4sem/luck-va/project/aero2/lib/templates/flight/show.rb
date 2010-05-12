"
<table class = 'list'>
  <tbody>
    <tr>
      <th>
        Номер рейса:
      </th>
      <th>
        #{@item[:code]}
      </th>  
    </tr>
    <tr>
      <th>
        Вылет (город, аэропорт):
      </th>
      <th>  
        #{@item[:departure_place]}, #{@item[:departure_airport]}
      </th>
    </tr>
    <tr>
      <th>
        Дата вылета:
      </th>
      <th>  
        #{@item[:departure_date]}
      </th>
    </tr>
    <tr>
      <th>
        Посадка (город, аэропорт):
      </th>
      <th>  
        #{@item[:arrival_place]}, #{@item[:arrival_airport]}
      </th>
    </tr>
    <tr>
      <th>
        Дата посадки:
      </th>
      <th>  
        #{@item[:arrival_date]}
      </th>
    </tr>
    <tr>
      <th>
        Авиакомпания:
      </th>
      <th>  
        <a href = 'aero.rb?controller=Company&action=show&company_id=#{@item[:id]}'>#{@item.company_name}</a>
      </th>
    </tr>
    <tr>
      <th>
        Статус рейса:
      </th>
      <th>  
	" +
	if @item.statuses and @item.statuses.size > 0
	  FlightStatus::STATUSES[@item.statuses[-1][:status]] + ', ' + @item.statuses[-1][:event_date].to_s +
        "<a href = 'aero.rb?controller=FlightStatus&action=show&flight_id=#{@item[:id]}'>История статусов</a>"
	else
	  'Неизвестно.'
	end +
	"
      </th>
    </tr>
    <tr>
      <th>
        Посадочные терминалы:
      </th>
      <th>" +
	if @item.terminals and @item.terminals.size > 0 
          @item.terminals.map do |ft| 
            "<a href = 'aero.rb?controller=FlightTerminal&action=show&terminal_id=#{ft[:id]}'>" + ft.terminal[:name] + "</a>" if ft.terminal
          end.join(", ") +	
        "<a href = 'aero.rb?controller=Terminal&action=list'>Список терминалов</a>"
	else
	  'У рейса нет посадочных терминалов'
	end +
        "
      </th>
    </tr>
    <tr>
      <th>
        Регистрационные стойки:
      </th>
      <th>" +
	if @item.check_in_desks and @item.check_in_desks.size > 0
          @item.check_in_desks.map do |ct| 
            "<a href = 'aero.rb?controller=FlightCheckInDesk&action=show&id=#{ct[:id]}'>" + ct.check_in_desk[:name] + "</a>" if ct.check_in_desk
          end.join(", ") + 
        "<a href = 'aero.rb?controller=CheckInDesk&action=list'>Список регистрационных стоек</a>"
	else
	  'У рейса нет регистрационных стоек'
 	end +
      "
      </th>
    </tr>
    " +
    if @user and !@user[:is_super]
    "
    <tr>
      <th>
        Действия:
      </th>
      <th>
        <a href = 'aero.rb?controller=Flight&action=destroy&id=#{@item[:id]}'>Удалить</a> | 
        <a href = 'aero.rb?controller=Flight&action=edit&id=#{@item[:id]}'>Редактировать</a>
      </th>  
    </tr>
    "
    else
      ''
    end +
    "
  </tbody>
</table>
"
