count = 0
"
<table class = 'list'>
  <caption>
    <a href = 'aero.rb?controller=#{@controller}&action=edit'>Создать новую запись</a>
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
      " +
      if @user and !@user[:is_super]
      "
      <td>
        <a href = 'aero.rb?controller=#{@controller}&action=edit&id=#{@id}'>Изменить статус рейса</a>
        <a href = 'aero.rb?controller=#{@controller}&action=destroy&id=#{@id}'>Удалить всю историю</a>
      </td>
      "
      else
        ''
      end +
      "
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"