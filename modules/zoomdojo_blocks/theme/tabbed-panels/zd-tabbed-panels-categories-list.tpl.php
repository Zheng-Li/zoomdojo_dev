<div>
    <?php if(!empty($categories)): ?>
        <table>
            <thead>
                <tr>
                    <th>Сategory</th>
                    <th>Weight</th>
                    <th width="100px">Operations</th>
                </tr>
            </thead>
            <tbody>
                <?php foreach ($categories as $category): ?>
                    <tr>
                        <td><?php print $category->title; ?> (<?php print $category->language; ?>)</td>
                        <td><?php print $category->weight; ?></td>
                        <td>
                            <a href="/admin/zoomdojo/tablet-panel/categories/edit/<?php print $category->id?>">Edit</a>
                            <a href="" data-url="<?php print $category->id?>" class="zd-delete-tab-category">Delete</a>
                        </td>
                    </tr>
                <?php endforeach; ?>
            </tbody>
        </table>
    <?php else: ?>
        <div>No any category</div>
    <?php endif; ?>
</div>