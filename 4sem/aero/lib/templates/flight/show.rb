"
<table class = 'list'>
  <caption>
    #{@header}<br />
    <span style = 'color: Red;'>#{@message}</span>
  </caption>

  <thead>
  <tbody>
    <tr>
      <th>Номер рейса:</th>
      <td>#{@item[:code]}</td>
    </tr>
    <tr>
      <th>
        Вылет<br>
        <div style = 'margin-left: 10px;'>город:</div>
        <div style = 'margin-left: 10px;'>время:</div>
        <div style = 'margin-left: 10px;'>аэропорт:</div>
      </th>
      <td>
        &nbsp;<br>
        #{@item[:departure_place]}<br>
        #{@item[:departure_date]}<br>
        #{@item[:departure_airport]}
      </td>
    </tr>
    <tr>
      <th>
        Посадка<br>
        <div style = 'margin-left: 10px;'>город:</div>
        <div style = 'margin-left: 10px;'>время:</div>
        <div style = 'margin-left: 10px;'>аэропорт:</div>
      </th>
      <td>
        &nbsp;<br>
        #{@item[:arrival_place]}<br>
        #{@item[:arrival_date]}<br>
        #{@item[:arrival_airport]}
      </td>
    </tr>
    <tr>
      <th>Авиакомпания:</th>
      <td>#{@item.company_name}</td>
    </tr>
    <tr>
      <th>Каким рейс является для нашего аэропорта:</th>
      <td>#{@item[:is_departure] ? 'Вылетающий' : 'Прилетающий'}</td>
    </tr>
    <tr>
      <th>Текущий статус:</th>
      <td>#{status(@item)}</td>
    </tr>
    <tr>
      <th>
        Регистрационные стойки<br>
      </th>
      <td>
      <table class = 'list'>
      <tbody>" +
@item.check_in_desks(@db).map do |cd|
  "<tr><th>#{view_link(:CheckInDesk, cd[:id], cd[:name])}</th>
  <td>#{view_link(:CheckInDeskFlight, cd[:cdf_id])}</td></tr>"
end.join("<br/>") +
  "</tbody>
</table>
      </td>
    </tr>
    <tr>
      <th>
        Список терминалов<br>
      </th>
      <td>
      <table class = 'list'>
<tbody>" +
@item.terminals(@db).map do |t|
  "<tr><th>#{view_link(:Terminal, t[:id], t[:name])}</th>
  <td>#{view_link(:FlightTerminal, t[:ft_id])}</td></tr>"
end.join("<br/>") +
 "</tbody>
</table>
      </td>
    </tr>
  </tbody>
</table>



"

