count = 0
"
<table class = 'list'>
  <caption>
    <a href = 'aero.rb?controller=Crew&action=edit'>Создать новую запись</a>
  </caption>
  <thead>
    <tr>
      <th>
        Пилот
      </th>
      <th>
        Второй пилот
      </th>
      <th>
        Стюард
      </th>
      <th>
        Второй стюард
      </th>
      <th>
        Бортмеханик
      </th>
      <th>
        Рейс
      </th>
      <th>
        Действия
      </th>
    </tr>
  </thead>
  <tbody>
" + @items.map do |i|
      count += 1
"
    <tr class = 'list#{count%2}'>
      <td>#{i.pilot[:surname]}</td>
      <td>#{i.second_pilot[:surname]}</td>
      <td>#{i.stuard[:surname]}</td>
      <td>#{i.second_stuard[:surname]}</td>
      <td>#{i.mechanic[:surname]}</td>
      <td>#{i.flight ? i.flight[:code] : 'Нет рейса'}</td>
      <td><a href='aero.rb?controller=Crew&action=choose_flight&id=#{i[:id]}'>#{i.flight ? 'Редактировать рейс' : 'Назначить рейс'}</a></td>
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"
