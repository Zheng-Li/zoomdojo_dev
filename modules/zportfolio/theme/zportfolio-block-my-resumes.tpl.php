<?php if (!empty($resumes)): ?>
    <ul>
        <?php foreach ($resumes as $resume): ?>
            <li>
                <a href="/z-portfolio-resume-edit/<?php print $resume->id; ?>"><?php print $resume->name; ?></a>
            </li>
        <?php endforeach; ?>
    </ul>
    <div class="z-view-all-resumes text-right">
        <a href="/all-my-resumes"><?php print t('View All Résumés'); ?></a>
    </div>
<?php endif; ?>