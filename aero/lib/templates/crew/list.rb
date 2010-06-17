count = 0
"
<table class = 'list'>
  <caption>
    <a href = 'aero.rb?controller=Crew&action=edit'>Создать новую запись</a>
  </caption>
  <thead>
    <tr>
      <th>
        Название
      </th>
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
" + 
if @items != []
@items.map do |i|
      count += 1
"
    <tr class = 'list#{count%2}'>
      <td><a href='aero.rb?controller=Crew&action=show&id=#{i[:id]}'>#{i[:name]}</a></td>
      <td>#{i.pilot[:second_name]}</td>
      <td>#{i.second_pilot[:second_name]}</td>
      <td>#{i.stuard1[:second_name]}</td>
      <td>#{i.stuard2[:second_name]}</td>
      <td>#{i.mechanic[:second_name]}</td>
      <td>#{i.flight ? i.flight[:code] : 'Нет рейса'}</td>
      <td>
      <a href='aero.rb?controller=Crew&action=choose_flight&id=#{i[:id]}'>#{i.flight ? 'Редактировать рейс' : 'Назначить рейс'}</a><br>
      <a href='aero.rb?controller=Crew&action=destroy&id=#{i[:id]}'> Удалить</a>
</td>
    </tr>
"
end.join("\n") 
else
""
end + "
  </tbody>
</table>
"
