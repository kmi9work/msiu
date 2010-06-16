count = 0
"
<table class = 'list'>
  <caption>
    #{@header}
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
        Дополнительная информация
      </th>
        <th>
        Номер рейса
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
      <td>#{i[:flight_id]}</td>
      <td>#{i[:info]}</td>
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"
