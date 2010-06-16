count = 0
"
<table class = 'list'>
  <caption>
    <a href = 'aero.rb?controller=#{@controller}&action=edit'>Создать новую запись</a>
  </caption>
  <thead>
    <tr>
      <th>
        Фамилия
      </th>
      <th>
        Имя
      </th>
      <th>
        Отчество
      </th>
      <th>
        № паспорта
      </th>
      <th>
        № Загран. парпорта
      </th>
      <th>
        Номер рейса
      </th>
      <th>
        Доп. информация
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
    <tr class = 'list#{count % 2}'>
      <td>#{i[:surname]}</td>
      <td>#{i[:name]}</td> 
      <td>#{i[:patronymic]}</td> 
      <td>#{i[:npass_i]}</td>
      <td>#{i[:npass_e]}</td>
      <td>#{i.flight[:code]}</td>
      <td>#{i[:info]}</td>
      <td>
        <a href = 'aero.rb?controller=#{@controller}&action=edit&id=#{i[:id]}'>Редактировать</a>
        <a href = 'aero.rb?controller=#{@controller}&action=destroy&id=#{i[:id]}'>Удалить</a>
      </td>
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"
