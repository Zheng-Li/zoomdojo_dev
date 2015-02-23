<div>
    <div id="tabs">
        <ul>
            <li><a href="#tabs-1">Nodes</a></li>
            <li><a href="#tabs-2">Taxonomy</a></li>
        </ul>
        <div id="tabs-1">
            <?php if(!empty($nodesType)): ?>
                <table>
                    <thead>
                        <tr>
                            <th>Title</th>
                            <th>Count links</th>
                            <th width="100px">Operations</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php foreach ($nodesType as $val): ?>
                            <tr>
                                <td><?php print $val->title; ?></td>
                                <td><?php print $val->count; ?></td>
                                <td>
                                    <a href="/admin/zoomdojo/tablet-panel/tabs/edit/<?php print $val->etity_id; ?>/<?php print $val->type; ?>">Edit</a>
                                    <a href="#" data-url="<?php print $val->etity_id; ?>" data-type="<?php print $val->type; ?>" class="zd-delete-tab-block">Delete</a>
                                </td>
                            </tr>
                        <?php endforeach; ?>
                    </tbody>
                </table>
            <?php else: ?>
                <div>No any blocks</div>
            <?php endif; ?>
        </div>
        <div id="tabs-2">
            <?php if(!empty($taxonomyType)): ?>
                <table>
                    <thead>
                        <tr>
                            <th>Title</th>
                            <th>Count links</th>
                            <th width="100px">Operations</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php foreach ($taxonomyType as $val): ?>
                            <tr>
                                <td><?php print $val->title; ?></td>
                                <td><?php print $val->count; ?></td>
                                <td>
                                    <a href="/admin/zoomdojo/tablet-panel/tabs/edit/<?php print $val->etity_id; ?>/<?php print $val->type; ?>">Edit</a>
                                    <a href="#" data-url="<?php print $val->etity_id; ?>" data-type="<?php print $val->type; ?>" class="zd-delete-tab-block">Delete</a>
                                </td>
                            </tr>
                        <?php endforeach; ?>
                    </tbody>
                </table>
            <?php else: ?>
                <div>No any blocks</div>
            <?php endif; ?>
        </div>
    </div>
</div>