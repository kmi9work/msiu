count = 0
"
<table class = 'list'>
  <caption>
    <a href = 'aero.rb?controller=#{@controller}&action=edit&flight_id=#{@id}'>Изменить статус рейса</a>
  </caption>
  <thead>
    <tr>
      <th>
        Статус
      </th>
      <th>
        Время
      </th>
    </tr>
  </thead>
  <tbody>
" + @items.map do |i|
      count += 1
"
    <tr class = 'list#{count % 2}'>
      <td>#{FlightStatus::STATUSES[i[:status]]}</td>
      <td>#{i[:event_date]}</td>
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"
